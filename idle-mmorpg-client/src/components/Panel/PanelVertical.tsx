import "./Panel.css";
import React from "react";
import { Panel } from "./Panel";

interface PanelVerticalProps extends React.HTMLAttributes<HTMLDivElement> {
    children: React.ReactNode;
    className?: string;
}

export const PanelVertical: React.FC<PanelVerticalProps> = ({
    children,
    className = "",
    ...props
}) => {
    return (
        <Panel className={`panel-vertical ${className}`} {...props}>
            {children}
        </Panel>
    );
};
